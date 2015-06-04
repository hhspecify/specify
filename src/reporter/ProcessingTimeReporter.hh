<?hh //strict

/**
 * This file is part of specify.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace specify\reporter;

use specify\LifeCycleEvent;
use specify\LifeCycleMessageSubscriber;
use specify\event\ExamplePackageStart;
use specify\event\ExamplePackageFinish;
use specify\io\ConsoleOutput;
use specify\io\Console;


final class ProcessingTimeReporter implements LifeCycleMessageSubscriber
{

    public function __construct(
        private Console $writer = new ConsoleOutput()
    )
    {
    }

    public function handle(LifeCycleEvent $event) : void
    {
        if ($event instanceof ExamplePackageFinish) {
            $this->onExamplePackageFinish($event);
        }
    }

    private function onExamplePackageFinish(ExamplePackageFinish $event) : void
    {
        $processingTime = $event->getProcessingTime();
        $this->writer->write("Finished in %F seconds\n", $processingTime);
    }

}
