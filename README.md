# pynw

A Python module for Needleman-Wunsch alignment, coded in C.

Credit to [this project](https://github.com/noporpoise/seq-align).

# Features

- Python 2 and 3 compatible

# Subtleties about sequence similarity

Aligners (like Needleman-Wunsch) try to maximize alignment score, not sequence
similarity. For example, if the aligner is run with a match score of $S_M$, a
mismatch penalty of $S_X > 0$, and a linear gap penalty of $S_G > 0$, then the
aligner finds an alignment with number of matches $M$, number of mismatches
$X$, number of insertions $I$, and number of deletions $D$ such that the
quantity $M S_M - X S_X - (I + D) S_G$ is maximized.

On the other hand, the sequence similarity between two aligned sequences is the
number of matched sites divided by the length of the alignment, that is, $M /
(l_1 + D)$, where $l_1$ is the length of the first sequence. It's not obvious
that these two things lead to the same result.

In theory, we want the alignment that optimizes the sequence similarity. More
practically, the aligner should output the optimal alignment (there can be more
than one alignment with the best score) that maximizes the sequence similarity.
Right now, the aligner just spits out one of the best alignments, and I'm just
hoping that that's generally a good idea.

# To do

- Try the timing versus the other options
- Compare the distances against the gold standard
