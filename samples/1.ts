function hello(i: int): int {
    let x: double = 12;
    console.log(x * i);
    return 0;
}

function main(): int32 {
    let arg: int = 10;
    hello(arg);
    return 0;
}