The test env is Oracle Linux 6.

Make sure rpmdevtools and rpm-build are installed.

1. Run `rpmdev-setuptree` to generate /root/rpmbuild automatically.

2. Run `rpmdev-newspec helloc.spec` inside /root/rpmbuild/SPECS.

3. Edt helloc.spec.

4. Copy helloc.c to folder helloc-0.1, run:

# tar zcvf helloc-0.1.tar.gz helloc-0.1
# mv helloc-0.1.tar.gz /root/rpmbuild/SOURCES

5. rpmbuild -ba SPECS/helloc.spec
