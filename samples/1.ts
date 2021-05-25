class ClassName {
    i: int;
    j: float;
    k: double;
    l: boolean;

    b(): int {
        return 1;
    }

    a(m: int): boolean {
        console.log(this.l);
        console.log(this.b());
        return false;
    };
}

function main(): int {

    let l = new ClassName();

    if (l.a(0)) {
        console.log("Hello world")
    } else {
        console.log("There is no hello world!.")
    }

    return 0;
}