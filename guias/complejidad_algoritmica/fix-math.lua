-- removes all `$$` surrounding align contexts

function walk_blocks(blocks)
  local new_blocks = {}
  for _, blk in ipairs(blocks) do
    if blk.t == 'Para' then
      -- Paras can contain inline math elements, so check and replace those as well
      local new_inlines = {}
      for _, inline in ipairs(blk.content) do
        if inline.t == 'Math' and inline.mathtype == 'DisplayMath' then
          if inline.text:match('^\\begin{align%*?}') then
            -- Replace inline Math with RawBlock (convert Para to RawBlock)
            table.insert(new_blocks, pandoc.RawBlock('latex', inline.text))
          else
            table.insert(new_inlines, inline)
          end
        else
          table.insert(new_inlines, inline)
        end
      end
      -- Only add the Para if there is still content
      if #new_inlines > 0 then
        table.insert(new_blocks, pandoc.Para(new_inlines))
      end

    elseif blk.t == 'Plain' then
      -- Similar handling for Plain blocks
      local new_inlines = {}
      for _, inline in ipairs(blk.content) do
        if inline.t == 'Math' and inline.mathtype == 'DisplayMath' then
          if inline.text:match('^\\begin{align%*?}') then
            table.insert(new_blocks, pandoc.RawBlock('latex', inline.text))
          else
            table.insert(new_inlines, inline)
          end
        else
          table.insert(new_inlines, inline)
        end
      end
      if #new_inlines > 0 then
        table.insert(new_blocks, pandoc.Plain(new_inlines))
      end

    elseif blk.t == 'CodeBlock' or blk.t == 'RawBlock' then
      -- Just keep them as is
      table.insert(new_blocks, blk)

    elseif blk.t == 'BlockQuote' or blk.t == 'Div' then
      -- Recurse on nested blocks
      blk.content = walk_blocks(blk.content)
      table.insert(new_blocks, blk)

    else
      -- Other block types just pass through
      table.insert(new_blocks, blk)
    end
  end
  return new_blocks
end

function Pandoc(doc)
  doc.blocks = walk_blocks(doc.blocks)
  return doc
end
