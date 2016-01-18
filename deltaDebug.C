#include "fvCFD.H"
#include "OFstream.H"

int main(int argc, char *argv[]) 
{
    #include "setRootCase.H"
    #include "createTime.H"
    #include "createMesh.H"

    volScalarField T
    (
        IOobject
        (
            "T",
            runTime.timeName(),
            mesh,
            IOobject::MUST_READ,
            IOobject::AUTO_WRITE
        ),
        mesh
    );

    T.correctBoundaryConditions();
    forAll(T.boundaryField(), patchI)
    {
        fvPatchField<scalar>& patch = T.boundaryField()[patchI];
        if (patch.type() == "fixedGradient")
        {
            const fvPatch& p = patch.patch();
            Info << "*** myDelta " << p.nf()*(p.nf() & (p.Cf() - p.Cn())) << endl;
            Info << "*** ofDelta " << p.delta() << endl;
        }
    }
}
