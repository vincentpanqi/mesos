/**
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <gtest/gtest.h>

#include <stout/gtest.hpp>
#include <stout/try.hpp>

#include "zookeeper/url.hpp"

TEST(ZooKeeper, URL)
{
  Try<zookeeper::URL> url =
    zookeeper::URL::parse("zk://host1:port1");
  EXPECT_SOME(url);
  EXPECT_TRUE(url.get().authentication.isNone());
  EXPECT_EQ("host1:port1", url.get().servers);
  EXPECT_EQ("/", url.get().path);

  url = zookeeper::URL::parse("zk://jake:1@host1:port1");
  EXPECT_SOME(url);
  EXPECT_FALSE(url.get().authentication.isNone());
  EXPECT_EQ("digest", url.get().authentication.get().scheme);
  EXPECT_EQ("jake:1", url.get().authentication.get().credentials);
  EXPECT_EQ("host1:port1", url.get().servers);
  EXPECT_EQ("/", url.get().path);

  url = zookeeper::URL::parse("zk://jake:1@host1:port1/");
  EXPECT_SOME(url);
  EXPECT_FALSE(url.get().authentication.isNone());
  EXPECT_EQ("digest", url.get().authentication.get().scheme);
  EXPECT_EQ("jake:1", url.get().authentication.get().credentials);
  EXPECT_EQ("host1:port1", url.get().servers);
  EXPECT_EQ("/", url.get().path);

  url = zookeeper::URL::parse("zk://jake:1@host1:port1,host2:port2");
  EXPECT_SOME(url);
  EXPECT_FALSE(url.get().authentication.isNone());
  EXPECT_EQ("digest", url.get().authentication.get().scheme);
  EXPECT_EQ("jake:1", url.get().authentication.get().credentials);
  EXPECT_EQ("host1:port1,host2:port2", url.get().servers);
  EXPECT_EQ("/", url.get().path);

  url = zookeeper::URL::parse("zk://jake:1@host1:port1,host2:port2/");
  EXPECT_SOME(url);
  EXPECT_FALSE(url.get().authentication.isNone());
  EXPECT_EQ("digest", url.get().authentication.get().scheme);
  EXPECT_EQ("jake:1", url.get().authentication.get().credentials);
  EXPECT_EQ("host1:port1,host2:port2", url.get().servers);
  EXPECT_EQ("/", url.get().path);

  url =
    zookeeper::URL::parse("zk://jake:1@host1:port1,host2:port2/path/to/znode");
  EXPECT_SOME(url);
  EXPECT_FALSE(url.get().authentication.isNone());
  EXPECT_EQ("digest", url.get().authentication.get().scheme);
  EXPECT_EQ("jake:1", url.get().authentication.get().credentials);
  EXPECT_EQ("host1:port1,host2:port2", url.get().servers);
  EXPECT_EQ("/path/to/znode", url.get().path);
}
