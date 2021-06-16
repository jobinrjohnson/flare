function printf(formatString: string, params: bigint): void;

function getchar(): bigint;

class Console {

    getInt(): bigint {

        let final = 0;
        let isNegative = false;

        let ip: bigint;

        if ((ip = getchar()) == 45) {
            isNegative = true;
            ip = getchar();
        }

        while (ip >= 48 && ip <= 57) {
            final = final * 10 + (ip - 48);
            ip = getchar();
        }

        if (isNegative) {
            final = -final;
        }

        return final;

    }

}


function main(): bigint {

    let prompt: string = "%d Enter the number : ";
    printf(prompt, 1);

    let i = new Console();
    let n: bigint = i.getInt();

    printf("The input is %d", n);

    return 0;
}