<?hh //strict

namespace specify\specification;

use specify\Specification;
use \ReflectionClass;
use \ReflectionException;


class PackageSpecification
{

    private PackageNamespace $ns;
    private DirectoryPath $packageDirectory;

    public function __construct(
        SpecificationPackage $package)
    {
        $this->ns = (string) $package->at(0);
        $this->packageDirectory = realpath($package->at(1));
    }

    public function getNamespace() : PackageNamespace
    {
        return $this->ns;
    }

    public function getPackageDirectory() : DirectoryPath
    {
        return $this->packageDirectory;
    }

    public function resolve(SpecificationFile $file) : ReflectionClass
    {
        $relativeClass = $this->relativeClassFrom($file);
        $fullName = $this->ns . $relativeClass;

        try {
            $reflection = new ReflectionClass($fullName);
        } catch (ReflectionException $exception) {
            throw new NotSpecificationFileException();
        }

        if ($reflection->implementsInterface(Specification::class) === false) {
            throw new NotSpecificationFileException();
        }

        return $reflection;
    }

    private function relativeClassFrom(SpecificationFile $file) : string
    {
        $replaceTargets = [
            $this->packageDirectory . '/',
            '/',
            '.hh'
        ];
        $replaceValues = [
            '',
            '\\',
            ''
        ];

        $relativeClass = str_replace($replaceTargets, $replaceValues, $file);

        return $relativeClass;
    }

}
