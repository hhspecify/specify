<?hh //strict

/**
 * This file is part of specify.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace specify\result;

use specify\VerifyResult;

class ExamplePackageResult implements VerifyResult
{

    public function __construct(
        private string $description,
        private ExampleGroupResultCollection $exampleGroupResults
    )
    {
    }

    public function getDescription() : string
    {
        return $this->description;
    }

    public function getExampleGroupResults() : ExampleGroupResultCollection
    {
        return $this->exampleGroupResults;
    }

    <<__Memoize>>
    public function getExampleCount() : int
    {
        $exampleCount = 0;
        $groupResults = $this->exampleGroupResults->items();

        foreach ($groupResults as $groupResult) {
            $exampleCount += $groupResult->getExampleCount();
        }

        return $exampleCount;
    }

    <<__Memoize>>
    public function getPendingExampleCount() : int
    {
        $pendingExampleCount = 0;
        $groupResults = $this->exampleGroupResults->items();

        foreach ($groupResults as $groupResult) {
            $pendingExampleCount += $groupResult->getPendingExampleCount();
        }

        return $pendingExampleCount;
    }

    <<__Memoize>>
    public function getFailedExampleCount() : int
    {
        $failedExampleCount = 0;
        $groupResults = $this->exampleGroupResults->items();

        foreach ($groupResults as $groupResult) {
            $failedExampleCount += $groupResult->getFailedExampleCount();
        }

        return $failedExampleCount;
    }

    <<__Memoize>>
    public function isPassed() : bool
    {
        $result = true;
        $groupResults = $this->exampleGroupResults->getIterator();

        foreach ($groupResults as $groupResult) {
            if ($groupResult->isPassed()) {
                continue;
            }
            $result = false;
            break;
        }

        return $result;
    }

    public function isFailed() : bool
    {
        return $this->isPassed() === false;
    }

}
