// @ts-ignore
function printI(i: int): void;

// @ts-ignore
function main(): int {

    for (let i = 0; i < 10; i = i + 1) {
        printI(i);
        i = i + 1;
    }

    return 0;
}