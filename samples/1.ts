// @ts-ignore
function printI(i: int): void;

// @ts-ignore
function main(): int {

    let a: int[];

    a[3] = 4;

    let x = 1;

    for (let i = 0; i < 10; i = i + 1) {
        let b: int;
        b = 10;
        // a[i] = 0;
        // if (i != 3) {
        //     a[i] = i;
        // }
        printI(x);
    }

    return 0;
}