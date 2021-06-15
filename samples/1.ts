class HelloWorld {
    logToConsole(): void {
        console.log("\n\nHello\n\nWorld!");
        console.log("\n\nHello 2\n\nWorld!");
        console.log("\n\nHello 3\n\nWorld!");
        console.log("\n\nHello 4\n\nWorld!");
        console.log("\n\nHello 5\n\nWorld!");
        console.log("\n\nHello 6\n\nWorld!");
    }
}


function main(): int {

    let h = new HelloWorld();

    // let i = 10000000;
    // while (i > 100000) {
    //     console.log(i);
    //     i = i + i;
    // }

    h.logToConsole();

    return 0;
}