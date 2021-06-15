import * as cMod from "#stdio.h"

function mlog(a: int): void {
    console.log(a);
}

class HelloWorld {
    logToConsole(): void {
        mlog(1);
        mlog(2);
        mlog(3);
        mlog(4);
    }
}


function main(): int {

    let h = new HelloWorld();
    h.logToConsole();

    return 0;
}