function printString(msg: string): void;

// @ts-ignore
function main(): int {
    let a: string = "hello";
    printString(a);
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

    let g = "hello";
    g = g + "lll";
    let h = g;
    h = h + ";;;";

    if (h == g) {
        printString(g + "============");
    } else {
        printString(g + "============");
    }
    printString(h);

    return 0;
}