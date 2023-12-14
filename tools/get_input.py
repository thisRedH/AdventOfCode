import argparse
from datetime import datetime
import requests

SESSION = "<SESSION>"
USERAGENT = "https://github.com/thisRedH/AdventOfCode/blob/main/tools/get_input.py by thisRedH/14.12.23"

parser = argparse.ArgumentParser(description="Get input from adventofcode.com")
parser.add_argument("day", type=int, nargs='?', default=datetime.now().day)
parser.add_argument("-y", "--year", type=int, default=datetime.now().year)
parser.add_argument("--session", type=str, default=SESSION)
parser.add_argument("--useragent", type=str, default=USERAGENT)
args = parser.parse_args()

headers = {
    "Cookie": f"session={args.session}",
    "User-Agent": f"{args.useragent}",
}

re = requests.get(
    f"https://adventofcode.com/{args.year}/day/{args.day}/input",
    headers=headers
)

print(re.text)
