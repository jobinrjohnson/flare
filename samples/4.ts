// @ts-ignore
function printf(msg: string, value: int): void;

// @ts-ignore
function the(): void {
    throw "helllo world.";
    // return  1;
}

// @ts-ignore
function main(): int {

    try {
        printf("Entering try block, %d\n", 0);
        the();
        printf("Completed try block, %d\n", 1);
        // @ts-ignore
    } catch (e: int) {
        printf("Entering catch(e:int) block, %d\n", 2);
    } finally {
        printf("Entering finally block, %d\n", 3);
    }


    return 0;

}