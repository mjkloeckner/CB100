-- removes all `$$` surrounding \begin{align} and \begin{align*} contexts; also
-- modifies the space after and before equations by adding \vspace{...}
--
-- \begin{align} .. \end{align} adds more vertical space before and after than 
-- $$ .. $$ (or \[ \] in latex notation)

local eq_before_space = "-1em"
local eq_after_space = "0em"
local eq_align_before_space = "-0.75em"
local eq_align_after_space = "-0.75em"

local function vspace(amount)
    return pandoc.RawBlock('latex', '\\vspace{' .. amount .. '}')
end

function walk_blocks(blocks)
    local new_blocks = {}
    for _, blk in ipairs(blocks) do
        if blk.t == 'Para' then
            -- Paras can contain inline math elements, so check and replace those as well
            local new_inlines = {}
            for _, inline in ipairs(blk.content) do
                if inline.t == 'Math' and inline.mathtype == 'DisplayMath' then
                    table.insert(new_blocks, vspace(eq_before_space))
                    if inline.text:match('^\\begin{align%*?}') then
                        -- replace inline Math with RawBlock (convert Para to RawBlock)
                        table.insert(new_blocks, vspace(eq_align_before_space))
                        table.insert(new_blocks, pandoc.RawBlock('latex', inline.text))
                        table.insert(new_blocks, vspace(eq_align_after_space))
                    else
                        table.insert(new_blocks, pandoc.RawBlock('latex', '\\[' .. inline.text .. '\\]'))
                    end
                    table.insert(new_blocks, vspace(eq_after_space))
                else
                    table.insert(new_inlines, inline)
                end
            end
            -- Only add the Para if there is still content
            if #new_inlines > 0 then
                table.insert(new_blocks, pandoc.Para(new_inlines))
            end

        elseif blk.t == 'CodeBlock' or blk.t == 'RawBlock' then
            -- Just keep them as is
            table.insert(new_blocks, blk)

        elseif blk.t == 'BlockQuote' or blk.t == 'Div' then
            -- Recurse on nested blocks
            table.insert(new_blocks, vspace("0.5em"))
            blk.content = walk_blocks(blk.content)
            table.insert(new_blocks, blk)
            table.insert(new_blocks, vspace("0.5em"))

        elseif blk.t == 'BulletList' or blk.t == 'OrderedList' then
            -- process each item recursively
            for i, item in ipairs(blk.content) do
                blk.content[i] = walk_blocks(item)
            end
            table.insert(new_blocks, blk)

        elseif blk.t == 'Item' then
            blk.content = walk_blocks(blk.content)
            table.insert(new_blocks, blk)
        else
            table.insert(new_blocks, blk)
        end
    end
    return new_blocks
end

function Pandoc(doc)
    doc.blocks = walk_blocks(doc.blocks)
    return doc
end
