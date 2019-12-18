import subprocess

def check_case(problemNumber, expectedLastLine):
    output = subprocess.check_output(f"build/Problem{problemNumber}/Problem{problemNumber}")
    lastLine = str(output, 'utf-8').splitlines()[-1]
    lastLine = lastLine.strip()
    # str to force it to a string, strip in case it already was
    expectedLastLine = str(expectedLastLine).strip()
    print(f"Problem {problemNumber} ran, last line of output was {lastLine}. Expected {expectedLastLine}. {'Match!' if lastLine == expectedLastLine else 'No match!'}")

check_case(1, 233168)
check_case(2, 4613732)
check_case(3, 6857)
check_case(4, 906609)
check_case(5, 232792560)
check_case(6, 25164150)
check_case(7, 104743)
check_case(8, 23514624000)
check_case(9, 31875000)
check_case(10, 142913828922)
check_case(11, 70600674)
check_case(12, 76576500)
check_case(13, 5537376230)
check_case(14, 837799)
