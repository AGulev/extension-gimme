local M = {}

function M.error_message(input)
    return input:gsub("<unknown:(%d+)>", function(num_str)
        local unhashed = gimme.unhash_val(num_str)
        return (unhashed and unhashed~= "" and unhashed ~= "<unknown>") and unhashed or "<unknown:" .. num_str .. ">"
    end)
end

return M
