# MClient CLI

CLI version of [mclient](https://github.com/Streamer272/mclient).

## Features

- Real time 🔥️
- Sound included 🎧️
- Super fast 🐎️
- Cross platform 🖥️
- Easy to use 🌟️

---

## Installation

### From source

#### Requirements

- [openal](https://www.openal.org)
- [meson](https://mesonbuild.com)
- [ninja](https://ninja-build.org)

On Ubuntu:

```shell
sudo apt install gcc meson ninja-build libopenal1 libopenal-dev
```

#### Installation

```shell
meson build
cd build
ninja
sudo ninja install
```

---

### From GitHub releases

#### Requirements

- [curl](https://curl.se)

On Ubuntu:

```shell
sudo apt install curl
```

#### Installation

```shell
sudo curl https://github.com/Streamer272/mclient-cli/releases/download/0.1.0/mclient-cli-0.1.0 -o /usr/local/bin/mclient-cli
sudo chmod +x /usr/local/bin/mclient-cli
```

---

### Using MClient CLI

Simply run `mclient-cli` to connect to a server, the output should look like this

<img src="https://user-images.githubusercontent.com" />

Then you can just start typing (`.` or `-`), and every keypress will be send as an event to the server as well as play a sound depending on what you pressed.

When other users connect, you will **not** receive any kind of notification, when they start typing, a sound will be played on your computer.

### License

MClient CLI is licensed under the [MIT License](https://github.com/Streamer272/mclient-cli/blob/main/LICENSE)