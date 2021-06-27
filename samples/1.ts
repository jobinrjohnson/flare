function printf(msg: string, value: int): void;

class A {
    x: int;

    sayHello(): void {
        printf("Hello World, %d", this.x);
    }

}

function main(): int {

    let b: A = new A();
    b.sayHello();

    return 0;

}