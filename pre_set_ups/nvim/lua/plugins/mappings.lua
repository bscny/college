return {
    {
        "AstroNvim/astrocore",
        ---@type AstroCoreOpts
        opts = {
            mappings = {
                -- first key is the mode
                n = {
                    -- quick save with ctrl + s
                    ["<C-s>"] = { ":w<cr>", desc = "Save File" },

                    -- hit <crtl> + <Z> to undo, <ctrl> + <Y> to redo
                    ["<C-z>"] = { "u" },
                    ["<C-y>"] = { "<C-R>" },

                    -- hit <F3> and <F4> to toggle aerial pannel
                    ["<F3>"] = { ":AerialOpen<cr>" },
                    ["<F4>"] = { ":AerialClose<cr>" },

                    -- hit <alt> + arrow key to move between words
                    ["<C-Right>"] = { "w" },
                    ["<A-Right>"] = { "w" },
                    ["<M-Right>"] = { "w" },

                    -- hit <alt> + arrow key to move between words
                    ["<C-Left>"] = { "b" },
                    ["<A-Left>"] = { "b" },
                    ["<M-Left>"] = { "b" },

                    -- hit <shift> + <alt> + <f> to auto indent
                    ["<S-A-f>"] = { "ggVG=" },

                    -- hit <ctrl> + <v> yo paste
                    ["<C-v>"] = {"p"}
                },
                t = {
                    -- setting a mapping to false will disable it
                    -- ["<esc>"] = false,
                },
                i = {
                    -- quick save with ctrl + s
                    ["<C-s>"] = { "<Esc>:w<cr>", desc = "Save File" },

                    -- hit <crtl> + <Backspace> to delete a word
                    ["<Esc><BS>"] = { "<C-W>" },
                    ["<C-BS>"] = { "<C-W>" },
                    ["<A-BS>"] = { "<C-W>" },
                    ["<M-BS>"] = { "<C-W>" },

                    -- hit <crtl> + <Z> to undo, <ctrl> + <Y> to redo
                    ["<C-z>"] = { "<Esc>ui" },
                    ["<C-y>"] = { "<Esc>:redo<cr>i" },

                    -- hit <F3> and <F4> to toggle aerial pannel
                    ["<F3>"] = { "<Esc>:AerialOpen<cr>" },
                    ["<F4>"] = { "<Esc>:AerialClose<cr>i" },

                    -- hit <alt> + arrow key to move between words
                    ["<C-Right>"] = { "w" },
                    -- ["<A-Right>"] = { "w" },
                    -- ["<M-Right>"] = { "w" },
                    ["<Esc><Right>"] = { "<Esc><Right>wi" },

                    -- hit <alt> + arrow key to move between words
                    ["<C-Left>"] = { "<Esc>b" },
                    -- ["<A-Left>"] = { "<Esc>b" },
                    -- ["<M-Left>"] = { "<Esc>b" },
                    ["<Esc><Left>"] = { "<Esc>bi" },
                },
                v = {
                    -- hit <ctrl> + <c> to copy
                    ["<C-c>"] = { "y" }
                }
            },
        },
    },
    {
        "AstroNvim/astrolsp",
        ---@type AstroLSPOpts
        opts = {
            mappings = {
                n = {
                    -- this mapping will only be set in buffers with an LSP attached
                    K = {
                        function() vim.lsp.buf.hover() end,
                        desc = "Hover symbol details",
                    },
                    -- condition for only server with declaration capabilities
                    gD = {
                        function() vim.lsp.buf.declaration() end,
                        desc = "Declaration of current symbol",
                        cond = "textDocument/declaration",
                    },
                },
            },
        },
    },
}
