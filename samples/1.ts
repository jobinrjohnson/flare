class HelloWorld {
    logToConsole(): void {
        console.log("\n\nHello\n\nWorld!");
    }
}


function main(): int {

    let h = new HelloWorld();

    let i = 10000000;
    while (i > 100000) {
        console.log(i);
        i = i + i;
    }

    h.logToConsole();

    return 0;
}