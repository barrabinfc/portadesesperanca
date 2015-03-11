import distutils.core

distutils.core.setup(
    name="portadesperanca",
    packages = ["."],
    requires = ['pexpect (>= 2.4)'],
    )
