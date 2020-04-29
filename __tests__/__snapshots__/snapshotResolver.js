module.exports = {
    resolveSnapshotPath: (testPath, snapshotExtension) =>
        testPath
            .replace(/_test.js/, '_test.re' + snapshotExtension)
            .replace(/lib([/\\]js)([/\\]__tests__)/, '__tests__/__snapshots__'),

    resolveTestPath: (snapshotFilePath, snapshotExtension) =>
        snapshotFilePath.replace(snapshotExtension, '.js').replace('__snapshots__', 'lib/js'),

    testPathForConsistencyCheck: 'src/components/some.test.js',
};
