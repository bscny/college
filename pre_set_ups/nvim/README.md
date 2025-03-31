# AstroNvim Template

**NOTE:** This is for AstroNvim v5+

A template for getting started with [AstroNvim](https://github.com/AstroNvim/AstroNvim)

## 🛠️ Installation

#### Make a backup of your current nvim and shared folder

```shell
mv ~/.config/nvim ~/.config/nvim.bak
mv ~/.local/share/nvim ~/.local/share/nvim.bak
mv ~/.local/state/nvim ~/.local/state/nvim.bak
mv ~/.cache/nvim ~/.cache/nvim.bak
```

#### Create a new user repository from this template

Press the "Use this template" button above to create a new repository to store your user configuration.

You can also just clone this repository directly if you do not want to track your user configuration in GitHub.

#### Clone the repository

```shell
git clone https://github.com/<your_user>/<your_repository> ~/.config/nvim
```

#### Start Neovim

```shell
nvim
```

#### Custom notes

1. in order to use `<C-y>` to redo
    1. goto `~/.local/share/nvim` search for word `<C-y>` (use `<leader>` + `<f>` + `<w>` to search)
    2. change all the `<C-y>` to `<C-q>`
2. in order to use `<A-\`>` to toggle terminal
    1. goto `~/.local/share/nvim` search for word `F7` 
    2. add `direction=float` after `ToggleTerm`
    3. change all the `<F7>` to `<A-\`>`
3. in order to use `<C-_>` (ctrl + /) to comment/uncomment lines
    1. goto `~/.local/share/nvim` search for word `<Leader>/` (**Notice**, the Leader is in L not l)
    2. change all the `<Leader>/` to `<C-_>`
