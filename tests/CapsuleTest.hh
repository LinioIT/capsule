<?hh // strict

namespace Linio\Capsule;

use \DateTime;
use \DateTimeInterface;
use \DateTimeZone;

interface InterfaceStub
{

}

class DependencyStub implements InterfaceStub
{
    public function __construct(public string $data)
    {}
}

class ExampleStub
{
    public function __construct(public InterfaceStub $data)
    {}
}

class CapsuleTest extends \PHPUnit_Framework_TestCase
{
    public function testIsCreatingConfig(): void
    {
        $capsule = new Capsule();
        $this->assertEquals(new Map([]), $capsule->getConfig());
    }

    public function testIsRegisteringImplementations(): void
    {
        $capsule = new Capsule();
        $capsule->register(DateTimeZone::class, $capsule ==> new DateTimeZone('America/Montevideo'));
        $instance = $capsule->resolve(DateTimeZone::class);

        $this->assertEquals(new DateTimeZone('America/Montevideo'), $instance);
    }

    /**
     * @expectedException HH\InvariantException
     * @expectedExceptionMessage Resolved type incompatible with registered type: expected "DateTimeInterface", got "DateTimeZone".
     */
    public function testIsDetectingIncompatibleImplementations(): void
    {
        $capsule = new Capsule();
        $capsule->register(DateTimeInterface::class, $capsule ==> new DateTimeZone('America/Montevideo'));
        $capsule->resolve(DateTimeInterface::class);
    }

    public function testIsCreatingInstance(): void
    {
        $expectedInstance = new ExampleStub(new DependencyStub('bar'));

        $capsule = new Capsule();
        $capsule->register(InterfaceStub::class, $capsule ==> new DependencyStub('bar'));
        $instance = $capsule->createInstance(ExampleStub::class);

        $this->assertEquals($expectedInstance->data, $instance->data);
    }
}
