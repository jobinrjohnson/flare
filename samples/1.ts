// @ts-ignore
function printI(i: int): void;

// @ts-ignore
function main(): int {

    let a: int[];

    a[0] = 0;
    a[1] = 1;
    a[2] = 2;
    a[3] = 3;
    a[4] = 4;
    a[5] = 5;
    a[6] = 6;

    let x = 0;
    let y = 1;

    for (let i = 0; i < 7; i = i + 1) {
        printI(a[x]);
        // x = x+1;
    }

    return 0;
}