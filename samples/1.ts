function printString(msg: string): void;

// @ts-ignore
function main(): int {

    let x: string[];

    let i = 0;
    while (i < 10) {
        if (i % 2 == 0) {
            x[i] = "Hello world!.";
        } else {
            x[i] = "Hello world!. Odd";
        }
        if (i > 0) {
            printString(x[i - 1]);
        }
        i = i + 1;
    }

    return 0;
}