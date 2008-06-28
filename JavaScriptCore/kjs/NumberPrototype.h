// -*- c-basic-offset: 2 -*-
/*
 *  This file is part of the KDE libraries
 *  Copyright (C) 1999-2000 Harri Porten (porten@kde.org)
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 *
 */

#ifndef NumberPrototype_h
#define NumberPrototype_h

#include "NumberObject.h"

namespace KJS {

    /**
     * @internal
     *
     * The initial value of Number.prototype (and thus all objects created
     * with the Number constructor
     */
    class NumberPrototype : public NumberObject {
    public:
        NumberPrototype(ExecState*, ObjectPrototype*, FunctionPrototype*);
    };

} // namespace KJS

#endif // NumberPrototype_h
