# c_extension_1

Compile and use as follow ( MacOs ):

```
$ brew install php
$ git clone https://github.com/mitghi/experiment_php && cd ./experiment_php/c_extension_1
$ phpize
$ ./configure
$ make
$ make install
$ # create large file containing commas ( size must modulo 16 ) @ /tmp/big.txt
$ php -dextension=/opt/homebrew/Cellar/php/*/pecl/*/counter.so  demo.php
```
