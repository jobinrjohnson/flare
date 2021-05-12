function factorial(i: bigint): bigint {
    if (i == 1) {
        return 1;
    }
    return i + factorial(i - 1);
}

function main(): int {
    let x: bigint = 12;
    console.log(factorial(x));

    return 0;
}
