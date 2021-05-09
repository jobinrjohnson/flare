let b = 90;

function someFunctionName(i, j) {
    console.log(0);
}

function main() {
    let sum = 0;
    let i = 0;

    while (i < 10) {
        i = i + 1;
        sum = sum + i;
        someFunctionName();
    }
    console.log(sum);
    return 0;
}
