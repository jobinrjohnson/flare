// @ts-ignore
function printI(i: int): void;

// @ts-ignore
function main(): int {

    let a: int[];

    a[3] = 4;

    for (let i = 0; i < 10; i = i + 1) {
        if (i != 3) {
            a[i] = i;
        }
        printI(a[i]);
    }

    return 0;
}