# Miliways
## A Game, a Restaurant, and a Band


## Description
Miliways is a co-op dungeon-crawler. You and your partner in magic play as Lilac and Clover, a witch and miner respectively.


## Compiling

> [!NOTE]
> I've only tested compiling with GCC, however any C99-conformant compiler should work for this.

Miliways depends on two external libraries, [ENet](https://github.com/lsalzman/enet) and [Raylib](https://github.com/raysan5/raylib).

Follow the instructions given by the library repos to install them. In most cases, your package manager should have them.

Miliways uses [nob.h](https://github.com/tsoding/nob.h). Run `gcc nob.c -o nob` once to bootstrap the build system. 

On future compiles, you can call the `nob` executable, and it will handle building for you.

Upon a successful build, the server executable will be placed in `/build/server/`, and the client executable will be placed in `/build/client`.

## Running

> [!WARNING]
> Miliways does not care about security or safety at all. It is not intentionally malicious or expolitable, I just didn't want to worry about network security while writing it. You take full responsibility if you choose to run the client or server.

### Server
#### CLI parameters:
| Name | Type | Default | Description |
| ---- | ---- | ------- | ----------- |
| `--addr` | String | 0 | The server's address. If no address is passed, it uses the host machine's address. |
| `--port` | Integer | 0 | The server's port. If no port is passed, it uses an OS-assigned port. |

#### Examples:

`miliways-sv --port 1234`

Starts the server locally, on port 1234.

### Client
A UI for connecting to a server is planned. Until then, use the CLI flags.

#### CLI parameters:
| Name | Type | Default | Description |
| ---- | ---- | ------- | ----------- |
| `--addr` | String | - | The address of the game server to connect to. |
| `--port` | Integer | - | The port to connect to. |
| `--play-as` | String | - | Which character to play as. Either `clover` or `lilac`. |

#### Examples:
`miliways-cl --addr localhost --port 1234 --play-as clover`

Connect to a locally hosted server on port 1234, and try to join as Clover.

`miliways-cl --addr mw.example.org --port 5678 --play-as lilac`

Connect to a server hosted at `mw.example.org` on port 1234, and try to join as Lilac.


## Acknowledgements
	
Miliways is licensed under the MIT license. See LICENSE in the root of this repository for the license text.

Miliways uses the following third-party libraries:

1. [Raylib](https://github.com/raysan5/raylib) by Ramon Santamaria (raysan5), licensed under the Zlib license.
1. [ENet](https://github.com/lsalzman/enet) by Lee Salzman (lsalzman), licensed under the MIT license.
1. [nob.h](https://github.com/tsoding/nob.h) by Alexey Kutepov (rexim/Tsoding), licensed under the MIT license.

The mining gameplay, and original idea for this game, were inspired by [Stardew Valley](https://www.stardewvalley.net/)'s mines.

I had help on the gameplay and character designs by [Yoyo](https://github.com/leafcatmeow).