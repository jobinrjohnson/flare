function printf(formatString: int, params: int): void;
function printf(formatString: int): void;

function getchar(): int;

class Console {

    isNumericInputOk(ip: int): boolean {
        if (ip < 48) {
            return false;
        }
        if (ip > 57) {
            return false;
        }
        return true;
    }

    getInt(): int {

        let final = 0;
        let isNegative = false;

        let ip: int = getchar();

        if (ip == 45) {
            isNegative = true;
            ip = getchar();
        }

        while (this.isNumericInputOk(ip)) {
            final = final * 10 + (ip - 48);
            ip = getchar();
        }

        if (isNegative) {
            final = -final;
        }

        return final;

    }

}


function main(): int {

    printf("Enter the number : ");

    let i = new Console();
    let n: int = i.getInt();

    printf("The input is %d", n);

    return 0;
}