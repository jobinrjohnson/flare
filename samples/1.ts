// @ts-ignore
function printf(msg: string, value: int): void;

// let global_exception: int = 10;

// function printf(msg: string, value: double): void;
// function printf(msg: string, value: string): void;

// class A {
//     // x: int = 10;
//     // y: double;
//     // z: boolean;
//     // w: string = "hello";
//     //
//     // sayHello(): void {
//     //     this.x = this.x * 100;
//     //     printf("Hello World, %d\n", this.x);
//     // }
//
//     getValue(): int {
//         throw "helllo world.";
//         // return  1;
//     }
//
// }

function the(): void {
    throw "helllo world.";
    // return  1;
}

function main(): int {

    // let b: A = new A();
    // b.x = 20;

    try {
        printf("Exception start, %d\n", 0);
        // b.getValue();
        the();
        // let x: int = b.getValue();
        // b.x = x;
        // b.sayHello();
    } catch (e: int) {
        printf("Exception happened, %d\n", 0);
        return 1;
    }


    return 0;

}