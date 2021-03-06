.. _psl2bed:

`psl2bed`
=========

The ``psl2bed`` script converts 0-based, half-open ``[start-1, end)`` `Pattern Space Layout <http://genome.ucsc.edu/FAQ/FAQformat.html#format2>`_ (PSL) to unsorted, 0-based, half-open ``[start-1, end)`` extended BED-formatted data.

For convenience, we also offer ``psl2starch``, which performs the extra step of creating a Starch-formatted archive.

============
Dependencies
============

The ``psl2bed`` script requires Python, version 2.5 or greater.

This script is also dependent on input that follows the `PSL specification <http://genome.ucsc.edu/FAQ/FAQformat.html#format2>`_. 

.. tip:: Conversion of data which are PSL-like, but which do not follow the specification can cause ``IOError`` and other runtime exceptions. If you run into problems, please check that your input follows the PSL specification.

======
Source
======

The ``psl2bed`` and ``psl2starch`` conversion scripts are part of the binary and source downloads of BEDOPS. See the :ref:`Installation <installation>` documentation for more details.

=====
Usage
=====

The ``psl2bed`` script parses PSL from standard input and prints sorted BED to standard output. The ``psl2starch`` script uses an extra step to parse GFF to a compressed BEDOPS :ref:`Starch-formatted <starch_specification>` archive, which is also directed to standard output.

.. tip:: By default, all conversion scripts now output sorted BED data ready for use with BEDOPS utilities. If you do not want to sort converted output, use the ``--do-not-sort`` option. Run the script with the ``--help`` option for more details.

.. tip:: If you are sorting data larger than system memory, use the ``--max-mem`` option to limit sort memory usage to a reasonable fraction of available memory, *e.g.*, ``--max-mem 2G`` or similar. See ``--help`` for more details.

=======
Example
=======

To demonstrate these scripts, we use a sample GFF input called ``foo.gff`` (see the :ref:`Downloads <gff2bed_downloads>` section to grab this file). 

::

  psLayout version 3

  match   mis-    rep.    N's     Q gap   Q gap   T gap   T gap   strand  Q               Q       Q       Q       T               T       T       T       block   blockSizes      qStarts  tStarts
          match   match           count   bases   count   bases           name            size    start   end     name            size    start   end     count
  ---------------------------------------------------------------------------------------------------------------------------------------------------------------
  35      0       0       0       0       0       0       0       +       foo     50      15      50      chrX    155270560       40535836        40535871        1       35,     15,     40535836,
  34      2       0       0       0       0       0       0       +       foo     50      14      50      chrX    155270560       68019028        68019064        1       36,     14,     68019028,
  33      2       0       0       0       0       0       0       +       foo     50      14      49      chrX    155270560       43068135        43068170        1       35,     14,     43068135,
  35      2       0       0       0       0       0       0       +       foo     50      13      50      chr8    146364022       131572122       131572159       1       37,     13,     131572122,
  30      0       0       0       0       0       0       0       +       foo     50      14      44      chr6    171115067       127685756       127685786       1       30,     14,     127685756,
  30      0       0       0       0       0       0       0       +       foo     50      14      44      chr6    171115067       93161871        93161901        1       30,     14,     93161871,
  31      0       0       0       0       0       0       0       +       foo     50      13      44      chr5    180915260       119897315       119897346       1       31,     13,     119897315,
  30      0       0       0       0       0       0       0       +       foo     50      14      44      chr5    180915260       123254725       123254755       1       30,     14,     123254725,
  ...

We can convert it to sorted BED data in the following manner:

::

  $ psl2bed --headered < foo.psl
  chr1    30571100        30571135        foo     50      -       35      0       0       0       0       0       0       0       15      50      249250621       1       35,     0,      30571100,
  chr1    69592160        69592195        foo     50      -       34      1       0       0       0       0       0       0       15      50      249250621       1       35,     0,      69592160,
  chr1    107200050       107200100       foo     50      +       50      0       0       0       0       0       0       0       0       50      249250621       1       50,     0,      107200050,
  chr11   12618347        12618389        foo     50      +       39      3       0       0       0       0       0       0       8       50      135006516       1       42,     8,      12618347,
  chr11   32933028        32933063        foo     50      +       35      0       0       0       1       1       0       0       8       44      135006516       2       4,31,   8,13,   32933028,32933032,
  chr11   80116421        80116457        foo     50      +       35      1       0       0       0       0       0       0       14      50      135006516       1       36,     14,     80116421,
  chr11   133952291       133952327       foo     50      +       34      2       0       0       0       0       0       0       14      50      135006516       1       36,     14,     133952291,
  chr13   99729482        99729523        foo     50      +       39      2       0       0       0       0       0       0       8       49      115169878       1       41,     8,      99729482,
  chr13   111391852       111391888       foo     50      +       34      2       0       0       0       0       0       0       14      50      115169878       1       36,     14,     111391852,
  chr16   8149657 8149694 foo     50      +       36      1       0       0       0       0       0       0       13      50      90354753        1       37,     13,     8149657,
  ...

.. note:: By default, the ``psl2bed`` and ``psl2starch`` scripts work with headerless PSL data. If you have headered PSL output, use the ``--headered`` operator with either conversion script, as shown in the example above.

.. _psl2bed_downloads:

=========
Downloads
=========

* Sample PSL dataset: :download:`foo.psl <../../../../assets/reference/file-management/conversion/reference_psl2bed_foo.psl>`

.. |--| unicode:: U+2013   .. en dash
.. |---| unicode:: U+2014  .. em dash, trimming surrounding whitespace
   :trim:
