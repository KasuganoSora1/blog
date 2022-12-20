# for 循环

``` batch
for %%i in (./*) do (echo hello world)
````

# if 判断条件

``` batch
if str == "test" (
    条件体1
)else(
    条件体2
)
```

# 设置变量

## echo
``` batch
@echo off
```
关闭echo显示
``` batch
@echo off
echo hello world
```
![echo_off](./batch_pic/echo_off.png)
``` batch
@echo on
echo hello world
```
![echo_off](./batch_pic/echo_on.png)

## setlocal enabledelayedexpansion




