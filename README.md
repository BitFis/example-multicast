# Example multicast send and receive

## Build

```bash
mkdir -p ./build
cd ./build
cmake ../
make
```

## Run

demo send multicast and receive nothing (server only 1 socket).
`IPV6_MULITCAST_LOOP` disabled on socket.

```bash
./build/main server 
```

Only send a multicast message (`IPV6_MULITCAST_LOOP` default value)

```bash
./build/main client
```

Both server (`IPV6_MULITCAST_LOOP` disabled) and client running (`IPV6_MULITCAST_LOOP` default value).

```bash
./build/main both
```

Server with `IPV6_MULITCAST_LOOP` enabled.

```bash
./build/main server enabled
```

Client sending multicast with `IPV6_MULITCAST_LOOP` disabled.

```bash
./build/main server enabled
```

Both `IPV6_MULITCAST_LOOP` disabled.

```bash
./build/main both disabled
```

Both `IPV6_MULITCAST_LOOP` enabled.

```bash
./build/main both enabled
```
