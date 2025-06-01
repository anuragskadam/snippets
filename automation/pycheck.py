import sys

contents_out = []
contents_corr = []

with open("out.txt", 'r') as f:
    for line in f.readlines():
        contents_out.append(line.split())
with open("key.txt", 'r') as f:
    for i, line in enumerate(f.readlines()):
        contents_corr.append(line.split())

while contents_out and not contents_out[-1]:
    contents_out.pop()
while contents_corr and not contents_corr[-1]:
    contents_corr.pop()

if len(contents_corr) != len(contents_out):
    print("unequal number of lines", file=sys.stderr)
else:
    bad_lines = []
    for i, (j, k) in enumerate(zip(contents_out, contents_corr)):
        if j != k:
            bad_lines.append(i + 1);
    if bad_lines:
        print("bad_lines:", bad_lines, file=sys.stderr);
    else:
        print("\033[33mCorrect!\033[0m", file=sys.stderr)
