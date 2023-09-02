# CMX Test Application

This is a sample C++ application that demonstrates the usage of the `cmw-cmx` library.
It is intended to be used to expose exemplary and random metrics to be read by other `cmx-cmw` applications.

## Building

Before you begin, ensure that you have the following prerequisites:

- C++ compiler
- `cmw-cmx` library installed, for compiling from source see [Dockerfile](Dockerfile)

```shell
mkdir build
cd build
cmake ../src
make
```

## Usage

Command-line arguments:

- Argument 1: Instance Name (optional)
- Argument 2: Process Component (optional, `true` or `false`) - if `true`, the application will expose some basic metrics about the process itself
- Argument 3: Metric Name (optional)
- Argument 4: String1 Value (optional)
- Argument 5: String2 Value (optional)

### Example Usage

```sh
./main
./main my_instance_name process_component=true my_metric_name custom_string1 custom_string2
```

### Example Metrics

```shell
bash-4.2# ./main 
Enter loop
[4408]:INFO:process.c:250:cmx_process_update: Initialise process component for process id=4408
0
10

bash-4.2# /opt/app-root/src/cmw-cmx/tools/cmw-cmx-reader
Component: _ pid=4408
    name="process_name"
    mtime="Thu Jan 12 21:39:12 2023"
    type="STRING"
    current-size=4
    value="main"

    name="process_id"
    mtime="Thu Jan 12 21:39:12 2023"
    type="INT64"
    value="4408"

    name="hostname"
    mtime="Thu Jan 12 21:39:12 2023"
    type="STRING"
    current-size=12
    value="833e0cc8d762"

    name="start_time"
    mtime="Thu Jan 12 21:39:12 2023"
    type="INT64"
    value="1673559552"

    name="rusage.utime"
    mtime="Thu Jan 12 21:40:23 2023"
    type="INT64"
    value="35009"

    name="rusage.stime"
    mtime="Thu Jan 12 21:40:23 2023"
    type="INT64"
    value="7791"

    name="rusage.nvcsw"
    mtime="Thu Jan 12 21:40:23 2023"
    type="INT64"
    value="86"

    name="rusage.nivcsw"
    mtime="Thu Jan 12 21:40:23 2023"
    type="INT64"
    value="6"

Component: cmx_test_app pid=4408
    name="test_counter1"
    mtime="Thu Jan 12 21:40:23 2023"
    type="INT64"
    value="71"

    name="test_counter2"
    mtime="Thu Jan 12 21:40:23 2023"
    type="INT64"
    value="367"

    name="test_gauge1"
    mtime="Thu Jan 12 21:40:23 2023"
    type="INT64"
    value="38"

Component: cmx_test_app_second_component pid=4408
    name="test_gauge2"
    mtime="Thu Jan 12 21:40:23 2023"
    type="FLOAT64"
    value="20"

    name="test_bool"
    mtime="Thu Jan 12 21:40:22 2023"
    type="BOOL"
    value="1"

    name="prometheus_labels"
    mtime="Thu Jan 12 21:39:12 2023"
    type="STRING"
    current-size=13
    value="string1_value"

    name="test_string2"
    mtime="Thu Jan 12 21:39:12 2023"
    type="STRING"
    current-size=13
    value="string2_value"

Component: cmx_test_appmetric_name_test pid=4408
    name="sample_metric"
    mtime="Thu Jan 12 21:40:23 2023"
    type="FLOAT64"
    value="0"
```

## Building and Running in a Container

```shell
docker build -t cmx-test-app .
docker run -it --rm -v /dev/shm:/dev/shm cmx-test-app
```

Please note that the container needs to be run with a shared memory device mounted; otherwise, metrics won't be accessible from the host or other containers
