function printString(msg: string): void;

// @ts-ignore
function main(): int {
    let a: string = "hello";
    a = "Hello";
    let b = "World";
    printString(a + " " + b + "!");

    let c1 = "hello";
    let c2 = "hello w";

    if (c1 == c2) {
        printString("C1 and C2 are equal (" + c1 + ")");
    } else {
        printString("C1(" + c1 + ") != C2(" + c2 + ")");
    }
    if (c1 != c2) {
        printString("C1(" + c1 + ") != C2(" + c2 + ")");
    } else {
        printString("C1 and C2 are equal (" + c1 + ")");
    }

    return 0;
}