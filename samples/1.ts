// function printf(msg: string, value: int): void;
// function printf(msg: string, value: double): void;
function printf(msg: string, value: string): void;

class A {
    x: int;
    y: double;
    z: boolean;
    w: string;

    sayHello(): void {
        printf("Hello World, %s", this.w);
    }

}

function main(): int {

    let b: A = new A();
    b.sayHello();

    return 0;

}