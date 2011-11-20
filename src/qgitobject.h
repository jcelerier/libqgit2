/******************************************************************************
 * This file is part of the Gluon Development Platform
 * Copyright (c) 2011 Laszlo Papp <djszapi@archlinux.us>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

#ifndef LIBQGIT2_OBJECT_H
#define LIBQGIT2_OBJECT_H

#include "libqgit2_export.h"

#include <QtCore/QString>
#include <QtCore/QDateTime>
#include <QtCore/QSharedPointer>

#include <git2/object.h>

namespace LibQGit2
{
    class QGitRepository;
    class QGitOId;
    class QGitCommit;
    class QGitTag;
    class QGitTree;
    class QGitBlob;

    class LIBQGIT2_OBJECT_EXPORT QGitObject
    {
        public:

            /**
             * Creates a QGitObject that points to object. The pointer object becomes managed by
             * this QGitObject, and must not be passed to another QGitObject or closed outside this
             * object.
             */
            explicit QGitObject(git_object *object = 0);
            QGitObject(const QGitObject& other);

            ~QGitObject();

            QGitCommit toCommit() const;
            QGitTag toTag() const;
            QGitTree toTree() const;
            QGitBlob toBlob() const;

            bool isNull() const;

            /**
             * Get the id (SHA1) of a repository object
             *
             * In-memory objects created by git_object_new() do not
             * have a SHA1 ID until they are written on a repository.
             *
             * @return the SHA1 id
             */
            QGitOId oid() const;

            /**
             * Get the object type of an object
             *
             * @return the object's type
             */
            git_otype type() const;

            /**
             * Get the object type as a string
             */
            QString typeString() const;

            /**
             * Get the repository that owns this object
             *
             * @param obj the object
             * @return the repository who owns this object
             */
            QGitRepository owner() const;

            git_object* data() const;
            const git_object* constData() const;

        private:
            QSharedPointer<git_object> d;
    };
}

#endif // LIBQGIT2_OBJECT_H
