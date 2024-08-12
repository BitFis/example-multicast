# Example multicast send and receive

## Build

```bash
mkdir -p ./build
cd ./build
cmake ../
make
```

## Run

Start server with default `IPV6_MULITCAST_LOOP` value.

```bash
./build/main server 
```

Only send a multicast message (`IPV6_MULITCAST_LOOP` default value)

```bash
./build/main client
```

Use same socket for server and sending (`IPV6_MULITCAST_LOOP` default value).

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
