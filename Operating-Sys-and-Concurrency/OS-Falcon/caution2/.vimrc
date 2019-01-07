" reload .vimrc"
nnoremap <leader>rv :source $MYVIMRC<CR>

" Show line numbers
set number


" enable coloring
syntax enable
colorscheme desert

" set space between lines to  0
set linespace=0

" set incsearch
"set incsearch

"set backspace=indent,eol,start " Backspace for dummies


" Keep search matches in the middle of the window.
nnoremap n nzzzv
nnoremap N Nzzzv

nmap <F4> :wa<CR>
nmap <F5> :wa<CR> :make<CR>
nmap <F12> :wa<CR> :q<CR>
nmap <F3> :undo<CR>

imap <F4> <ESC>:wa<CR>
imap <F5> <ESC>:wa<CR> :make<CR>
imap <F12> <ESC>:wa<CR> :q<CR>
imap <F3> <ESC>:undo<CR> 

" navigate properly when lines are wrapped
nnoremap j gj
nnoremap k gk

"--------------[mouse/scroll]---------------"
map <ScrollWheelUp> 2<C-Y>
map <ScrollWheelDown> 2<C-E>
set mouse=a        " Enable mouse usage
set mousehide      " Hide the mouse cursor while typing

"------------------[Tabs]-------------------"
set smartindent
set smarttab
set tabstop=2
set softtabstop=2 
set shiftwidth=2
set noexpandtab

" fix indentation
nmap <F7> mzgg=G`zzz
imap <F7> <Esc>mzgg=G`zzza
