<?hh //strict

/**
 * This file is part of specify.
 *
 * (c) Noritaka Horio <holy.shared.design@gmail.com>
 *
 * This source file is subject to the MIT license that is bundled
 * with this source code in the file LICENSE.
 */

namespace specify\io;


class BufferWriter implements Writer
{

    public function write(string $value) : void
    {
        echo $value;
    }

    public function writeln(string $value) : void
    {
        echo $value, "\n";
    }

}
