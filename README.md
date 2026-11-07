# ESPhone packages

Package repository for the picoc-esp32 shell ("ESPhone"). Install
packages on the board with `pkg`.

## Using it on the board

```
wifi connect "MyNetwork" password
pkg repo https://raw.githubusercontent.com/USER/esphone-packages/main
pkg update
pkg list
pkg install uptime note textutils
```

Replace `USER` with your GitHub username (and `main` with your branch name if different).

## Packages

| Package | Commands | Shows how to… |
|---|---|---|
| `hello` | `hello [name]` | make the simplest package: one `.c` file |
| `fortune` | `fortune` | ship a data file (`/pkg/fortune/sayings.txt`) |
| `uptime` | `uptime` | use the ESP32 built-ins (`millis`, `free_heap`) |
| `note` | `note`, `note add TEXT`, `note clear` | keep user data that survives upgrades (not in `files.txt`) |
| `textutils` | `wc`, `head`, `grep` | put several commands in one package |
| `weather` | `weather [city]` | call a web API over https, with a default setting in `city.txt` |

## Layout

```
index.txt                     name  version  description - one per line
packages/NAME/files.txt       files to install, one per line
packages/NAME/*               the files
tools/check_repo.py           checks everything before you push
```

On the board, `.c` files go to `/bin` (they become commands), `NAME.man`
files go to `/man/NAME.txt` (shown by `man NAME`), and every other file
goes to `/pkg/NAME/`.

## Adding or changing a package

1. Create or edit `packages/NAME/` (each command needs a `NAME.c` and
   a `NAME.man`) and list the files in `files.txt`.
2. Add the package to `index.txt`, or **change its version** if it's already
   there. Boards only upgrade when the version changes.
3. Check it:

   ```bash
   python3 tools/check_repo.py
   ```

4. Commit and push. On the board: `pkg update`, then `pkg upgrade` or
   `pkg install NAME`.

## Testing without GitHub

```bash
python3 -m http.server 8000         # in this folder
```

On the board: `pkg repo http://YOUR-PC-IP:8000`, or in QEMU
`pkg repo http://10.0.2.2:8000`.

## Rules (enforced by `pkg` and `check_repo.py`)

- Package and command names: `a-z 0-9 - _`, up to 31 characters.
- Versions: no spaces, up to 15 characters.
- `files.txt`: up to 16 plain file names (no folders, no leading `.`, not
  `installed.txt`), under 2 KB.
- A command can't have the same name as a built-in one (`ls`, `cat`, …) or
  as a command in another package.
- Every command should have a `NAME.man` page: plain ASCII, lines up to
  40 columns, starting with a `NAME` section (`  cmd - summary`).
