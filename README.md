Linio Capsule
=============
[![Latest Stable Version](https://poser.pugx.org/linio/capsule/v/stable.svg)](https://packagist.org/packages/linio/capsule) [![License](https://poser.pugx.org/linio/capsule/license.svg)](https://packagist.org/packages/linio/capsule) [![Build Status](https://secure.travis-ci.org/LinioIT/capsule.png)](http://travis-ci.org/LinioIT/capsule)

Linio Capsule is a highly opinionated dependency injection container for Hack, helping you map
open generic abstractions to open generic implementations. It aims to take advantage of Hack's
features to provide a highly efficient, type-safe, non-invasive container. It also supports
dynamic wiring via constructor dependencies.

Install
-------

The recommended way to install Linio Capsule is [through composer](http://getcomposer.org).

```JSON
{
    "require": {
        "linio/capsule": "0.1.*"
    }
}
```

Tests
-----

To run the test suite, you need install the dependencies via composer, then
run PHPUnit.

    $ composer install
    $ bin/phpunit


Usage
-----

Preparing your capsule is quite simple. This is an example of a simple front-controller:

```hack
<?hh

require 'vendor/autoload.php';

use Linio\Capsule\Capsule;

class ExampleService
{
    public function __construct(protected \DateTimeInterface $date): void
    {
    }
}

$capsule = new Capsule();
$capsule->register(\DateTimeInterface::class, ($capsule) ==> new \DateTime());
$capsule->register(ExampleService::class, ($capsule) ==> new \ExampleService($capsule->resolve(\DateTimeInterface::class)));

$capsule->resolve(ExampleService::class); // Instance of ExampleService

```

Dynamic wiring
--------------

You can also leave the job to Capsule if you don't want to manually wire dependencies. This
feature depends on dependency injection via constructor arguments. Also, Capsule will only
autowrite non-optional dependencies.

```hack
<?hh

require 'vendor/autoload.php';

use Linio\Capsule\Capsule;

class ExampleService
{
    public function __construct(protected \DateTimeInterface $date): void
    {
    }
}

$capsule = new Capsule();
$capsule->register(\DateTimeInterface::class, ($capsule) ==> new \DateTime());
$capsule->resolve(ExampleService::class); // Instance of ExampleService autowired via DateTimeInterface

```
