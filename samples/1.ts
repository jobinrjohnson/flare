// @ts-ignore
function printf(format: string, arg: string): void;

class A {
    hello: int;
}

// @ts-ignore
function main(): int {

    let x: A = new A();

    let a: string = "90";
    printf("The number is %s", a);

    return 0;
}