// @ts-ignore
function printI(i: int): void;

// @ts-ignore
function main(): int {

    let a: int[];

    let y = 3;

    for (let i = 0; i < 5; i = i + 1) {
        let x = y + i;
        printI(i)
    }


    // let ctr = 0;
    // while(ctr < 10){
    //     printI(a[ctr])
    //     ctr = ctr + 1;
    // }

    return 0;
}