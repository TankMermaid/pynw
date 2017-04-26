#!/usr/bin/env python3

import argparse, subprocess

def counts(s1, s2):
    dat = {'match': 0, 'mismatch': 0, 'insert': 0, 'delete': 0}
    for c1, c2 in zip(s1, s2):
        if c1 == c2:
            dat['match'] += 1
        elif c1 == '-':
            dat['delete'] += 1
        elif c2 == '-':
            dat['insert'] += 1
        else:
            dat['mismatch'] += 1

    return dat

def hamming(s1, s2):
    assert len(s1) == len(s2)

    num = sum([1 for x, y in zip(s1, s2) if x != y])
    den = sum([1 for x, y in zip(s1, s2) if not (x == y and x in ['-', '.'])])

    return num / den

if __name__ == '__main__':
    p = argparse.ArgumentParser()
    p.add_argument('seq1')
    p.add_argument('seq2')
    p.add_argument('--match', default=1)
    p.add_argument('--mismatch', default=-2)
    p.add_argument('--gap', default=-2)
    p.add_argument('--gapopen', default=0)
    args = p.parse_args()

    res = subprocess.run(['/Users/scott/src/seq-align/bin/needleman_wunsch',
        '--match', str(args.match), '--mismatch', str(args.mismatch),
        '--gapopen', str(args.gapopen), '--gapextend', str(args.gap),
        args.seq1, args.seq2], stdout=subprocess.PIPE)

    a1, a2 = res.stdout.decode().split('\n')[0:2]
    #print(a1)
    #print(a2)
    print(hamming(a1, a2))
    #print(counts(a1, a2))
