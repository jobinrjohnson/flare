// @ts-ignore
function printf(format: string, arg: double): void;

class A {
    hello: int;

    sayHello(): void {
        // let hell:int = this.hello;
        // printf("The class number is %d", hell)
    }
}

// @ts-ignore
function main(): int {

    let x: A = new A();
    // x.sayHello();

    let a: double = 90.3;
    printf("The number is %f", a);

    return 0;
}