function printString(msg: string): void;

// @ts-ignore
function main(): int {
    let a: string = "hello";
    a = "Hello";
    let b = "World";
    printString(a + " " + b + "!");
    return 0;
}