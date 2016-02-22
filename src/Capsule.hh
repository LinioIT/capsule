<?hh // strict

namespace Linio\Capsule;

use \ReflectionClass;

class Capsule
{
    protected Map<string, (function (Capsule): mixed)> $registry = Map {};
    protected Map<string, mixed> $config = Map {};

    public function register<T>(classname<T> $alias, (function (Capsule): T) $resolver): void
    {
        $this->registry[$alias] = $resolver;
    }

    <<__Memoize>>
    public function resolve<T>(classname<T> $alias): T
    {
        $resolution = ($this->registry->contains($alias)) ? $this->registry[$alias]($this) : $this->createInstance($alias);
        invariant($resolution instanceof $alias, 'Resolved type incompatible with registered type: expected "%s", got "%s".', $alias, get_class($resolution));

        return $resolution;
    }

    public function createInstance<T>(classname<T> $alias): T
    {
        $class = new ReflectionClass($alias);
        $constructor = $class->getConstructor();

        if (!$constructor) {
            return $class->newInstance();
        }

        $arguments = Map {};
        foreach ($constructor->getParameters() as $parameter) {
            if ($parameter->isOptional()) {
                continue;
            }

            $arguments[$parameter->getName()] = $this->resolve($parameter->getTypehintText());
        }

        return $class->newInstanceArgs($arguments);
    }

    public function getConfig(): Map<string, mixed>
    {
        return $this->config;
    }
}
